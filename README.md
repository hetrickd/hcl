# HCl (Hydrochloric acid)

This is a simple arithmetic solver, designed to defeat (dissolve) tinsoldier's puzzles!
(see ##chat on irc.libera.chat to play)

## Usage

1. Compile the program

```bash
make
```
This produces the executable `./hcl`

2. Run the program with input from **stdin** in the following format:
```
TARGET; N1 N2 N3 ...
```
- `TARGET` is your target integer
- `N1 N2 N3 ...` is your number bank (maximum 6 currently)

Example:
```
echo "629; 50 5 1 3 6 6" | ./hcl
```

## License
See `LICENSE.txt`
