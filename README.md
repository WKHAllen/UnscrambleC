# UnscrambleC

A C program that unscrambles words.

## Usage

To use the unscrambler, simply run the program and pass the scrambled word as the primary argument.

```console
$ unscramble loelh
hello
```

If no word is provided, standard input will be used.

```console
$ unscramble
> cats
  | acts
  | cast
  | cats
  | scat
> else
  | eels
  | else
  | lees
>
$
```

To exit the standard input prompt, provide no input.

### Dictionaries

To use a different dictionary, use -d.

```console
$ unscramble -d british-english locoru
colour
```

More dictionaries can be found on any Unix system.
