# PONG

Classic two-player Pong in the terminal, written in C with ncurses.


## Dependencies

- `ncurses`
- `cdk` (Curses Development Kit — used for the menu)

Install on Debian/Ubuntu:
```bash
sudo apt install libncurses-dev libcdk5-dev
```
Install on Arch:
```bash
sudo pacman -S ncurses cdk
```
Install on macOS (Homebrew):
```bash
brew install ncurses cdk
```

## Build

```bash
make
```

## Run

```bash
./pong
```

## Controls

| Action | Player 1 | Player 2 |
|---|---|---|
| Move up | `W` | `↑` |
| Move down | `S` | `↓` |

## Roadmap

- [x] Difficulty setting (changes ball speed)
- [x] Loading screen (ASCII)
- [x] Portability improvements
- [] SIGWINCH support (terminal resize)
