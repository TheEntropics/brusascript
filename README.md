# The BrusaScript Translator

This command line tool allows you to translate any text to Brusa Language... or 
more simply to BURSA LNGUGIE H!?


## Specifications

Every source file in the repository have to be named LANGUAGE.xxx where `xxx` is the
extension needed by that language.

Each program should have this command line interface:

```shell
PROGRAM [filename]
```

If the `filename` parameter is missing the program has to read from the standard input.

## The algorithm

The algorithm is very simple and it's divided into some phases:
 1. Capitalize everything
 2. Swap some letters
    1. A pair of adjacent letters will be swapped with a probability of `20%`
    2. No more than 2 swaps per word
 3. Remove some letters
    1. Remove a letter with a probability of 5% if it is a vocal
    2. 20% if it's a consonant
    3. 40% if it's a double letter
 4. Add to the end of the line some `H!?`
    1. With a probability of 30%
