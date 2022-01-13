# Autocorrect

There are a lot of words that are prone to being typed incorrectly, due to habit, sequence or just user error.  This feature leverages your firmware to automatically correct these errors, to help reduce typos.

## How does it work? :id=how-does-it-work

The feature maintains a small buffer of recent key presses. On each key press, it checks whether the buffer ends in a recognized typo, and if so, automatically sends keystrokes to correct it.

The tricky part is how to efficiently check the buffer for typos. We don’t want to spend too much memory or time on storing or searching the typos. A good solution is to represent the typos with a trie data structure. A trie is a tree data structure where each node is a letter, and words are formed by following a path to one of the leaves.

![An example trie](https://getreuer.info/posts/keyboards/autocorrection/trie.svg)

Since we search whether the buffer ends in a typo, we store the trie writing in reverse. The trie is queried starting from the last letter, then second to last letter, and so on, until either a letter doesn’t match or we reach a leaf, meaning a typo was found.

## How do I enable Autocorrection :id=how-do-i-enable-autocorrection

In your `rules.mk`, add this: 

```make
AUTOCORRECT_ENABLE = yes
```

Additionally, you will need a library for autocorrection.  A small sample library is included by default, so that you can get up and running right away, but you can provide a customized library.   

By default, autocorrect is disabled.  To enable it, you need to use the `AUTOCORRECT_TOGGLE` keycode to enable it. The status is stored in persistent memory, so you shouldn't need to enabled it again.


### Customizing autocorrect library :id=customizing-autocorrect-library

To provide a custom library, you need to create a text file with the corrections.  For instance: 

```text
:thier        -> their
fitler        -> filter
lenght        -> length
ouput         -> output
widht         -> width
```

The syntax is `typo  ->  correction`. Typos and corrections are case insensitive, and any whitespace before or after the typo and correction is ignored. The typo must be only the letters a–z, or the special character : representing a word break. The correction may have any non-unicode characters.

Then, run: 

```sh
qmk generate-autocorrect-data autocorrect_dictionary.txt
```

This will process the file and produce an `autocorrect_data.h` file with the trie library, in the folder that you are at.  You can specify the keyboard and keymap (eg `-kb planck/rev6 -km jackhumbert`), and it will place the file in that folder instead. But as long as the file is located in your keymap folder, or user folder, it should be picked up automatically. 


This file will look like this: 

```c
// :thier        -> their
// fitler        -> filter
// lenght        -> length
// ouput         -> output
// widht         -> width

#define AUTOCORRECT_MIN_LENGTH 5  // "ouput"
#define AUTOCORRECT_MAX_LENGTH 6  // ":thier"

#define DICTIONARY_SIZE 74

static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {85, 7, 0, 23, 35, 0, 0, 8, 0, 76, 16, 0, 15, 25, 0, 0,
    11, 23, 44, 0, 130, 101, 105, 114, 0, 23, 12, 9, 0, 131, 108, 116, 101, 114, 0, 75, 42, 0, 24, 64, 0, 0, 71, 49, 0,
    10, 56, 0, 0, 12, 26, 0, 129, 116, 104, 0, 17, 8, 15, 0, 129, 116, 104, 0, 19, 24, 18, 0, 130, 116, 112, 117, 116,
    0};
```

!> The `autocorrect_data.h` file is excluded from git by default, so will not be included in git commits.

#### Avoiding false triggers :id=avoiding-false-triggers

By default, typos are searched within words, to find typos within longer identifiers like maxFitlerOuput. While this is useful, a consequence is that autocorrection will falsely trigger when a typo happens to be a substring of a correctly-spelled word. For instance, if we had thier -> their as an entry, it would falsely trigger on (correct, though relatively uncommon) words like “wealthier” and “filthier.”

The solution is to set a word break : before and/or after the typo to constrain matching. : matches space, period, comma, underscore, digits, and most other non-alpha characters.

|Text             |thier   |:thier  |thier:  |:thier: |
|-----------------|:------:|:------:|:------:|:------:|
|see `thier` typo |matches |matches |matches |matches |
|it’s `thiers`    |matches |matches |no      |no      |
|wealthier words  |matches |no      |matches |no      |

:thier: is most restrictive, matching only when thier is a whole word.

The `qmk generate-autocorrect-data` commands can make an effort to check for entries that would false trigger as substrings of correct words. It searches each typo against a dictionary of 25K English words from the english_words Python package, provided it’s installed. (run `python3 -m pip install english_words` to install it.)

?> Unfortunately, this is limited to just english words, at this point. 

### Overridding Autocorrect

Occasionally you might actually want to type a typo (for instance, while editing autocorrection_dict.txt) without being autocorrected. There are a couple of ways to do this: 
 
1. Begin typing the typo.
2. Before typing the last letter, press and release the Ctrl or Alt key.
3. Type the remaining letters.

This works because the autocorrection implementation doesn’t understand hotkeys, so it resets itself whenever a modifier other than shift is held.

Additionally, you can use the `AUTOCORRECT_TOGGLE` keycode to toggle the on/off status for Autocorrect. 

### Keycodes :id=keycodes

|Keycode              | Short keycode | Description                                    |
|`AUTOCORRECT_TOGGLE` | `AUTOCRT`     | Toggles the status of the Autocorrect feature. |

## Appendix: Trie binary data format :id=appendix

This section details how the trie is serialized to byte data in autocorrection_data. You don’t need to care about this to use this autocorrection implementation. But it is documented for the record in case anyone is interested in modifying the implementation, or just curious how it works.

What I did here is fairly arbitrary, but it is simple to decode and gets the job done.

### Encoding :id=encoding

All autocorrection data is stored in a single flat array autocorrection_data. Each trie node is associated with a byte offset into this array, where data for that node is encoded, beginning with root at offset 0. There are three kinds of nodes. The highest two bits of the first byte of the node indicate what kind:

* 00 ⇒ chain node: a trie node with a single child.
* 01 ⇒ branching node: a trie node with multiple children.
* 10 ⇒ leaf node: a leaf, corresponding to a typo and storing its correction.

![An example trie](https://getreuer.info/posts/keyboards/autocorrection/trie.svg)

**Branching node**. Each branch is encoded with one byte for the keycode (KC_A–KC_Z) followed by a link to the child node. Links between nodes are 16-bit byte offsets relative to the beginning of the array, serialized in little endian order.

All branches are serialized this way, one after another, and terminated with a zero byte. As described above, the node is identified as a branch by setting the two high bits of the first byte to 01, done by bitwise ORing the first keycode with 64. keycode. The root node for the above figure would be serialized like:

```
+-------+-------+-------+-------+-------+-------+-------+
| R|64  |    node 2     |   T   |    node 3     |   0   |
+-------+-------+-------+-------+-------+-------+-------+
```

**Chain node**. Tries tend to have long chains of single-child nodes, as seen in the example above with f-i-t-l in fitler. So to save space, we use a different format to encode chains than branching nodes. A chain is encoded as a string of keycodes, beginning with the node closest to the root, and terminated with a zero byte. The child of the last node in the chain is encoded immediately after. That child could be either a branching node or a leaf.

In the figure above, the f-i-t-l chain is encoded as

```
+-------+-------+-------+-------+-------+
|   L   |   T   |   I   |   F   |   0   |
+-------+-------+-------+-------+-------+
```

If we were to encode this chain using the same format used for branching nodes, we would encode a 16-bit node link with every node, costing 8 more bytes in this example. Across the whole trie, this adds up. Conveniently, we can point to intermediate points in the chain and interpret the bytes in the same way as before. E.g. starting at the i instead of the l, and the subchain has the same format.

**Leaf node**. A leaf node corresponds to a particular typo and stores data to correct the typo. The leaf begins with a byte for the number of backspaces to type, and is followed by a null-terminated ASCII string of the replacement text. The idea is, after tapping backspace the indicated number of times, we can simply pass this string to the `send_string_P` function. For fitler, we need to tap backspace 3 times (not 4, because we catch the typo as the final ‘r’ is pressed) and replace it with lter. To identify the node as a leaf, the two high bits are set to 10 by ORing the backspace count with 128:

```
+-------+-------+-------+-------+-------+-------+
| 3|128 |  'l'  |  't'  |  'e'  |  'r'  |   0   |
+-------+-------+-------+-------+-------+-------+
```

### Decoding :id=decoding

This format is by design decodable with fairly simple logic. A 16-bit variable state represents our current position in the trie, initialized with 0 to start at the root node. Then, for each keycode, test the highest two bits in the byte at state to identify the kind of node.

* 00 ⇒ **chain node**: If the node’s byte matches the keycode, increment state by one to go to the next byte. If the next byte is zero, increment again to go to the following node.
* 01 ⇒ **branching node**: Search the branches for one that matches the keycode, and follow its node link.
* 10 ⇒ **leaf node**: a typo has been found! We read its first byte for the number of backspaces to type, then pass its following bytes to send_string_P to type the correction.


## Credits

Credit goes to [getreuer](https://github.com/getreuer) for originally implementing this [here](https://getreuer.info/posts/keyboards/autocorrection/#how-does-it-work).  As well as to [filterpaper](https://github.com/filterpaper) for converting the code to use PROGMEM, and additional improvements.
