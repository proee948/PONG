# PONG

Classic two-player Pong in the terminal, written in C with ncurses.

##latest issues and bugs to fix:
- SIGWINCH_HANDLER should call ONLY asynchronous functions, it currently succesfully resizes loading menu but it fails miserably in game(), this requires extensive game() restructuring...
- CTRL+C is the only way out, tbh this is okay i see no problem but yeah will keep in mind...
- destroyCDKScreen(cdk) / endCDK() called in main but cdk only gets initialized inside menu() — if user picks START without going through menu again after resize, cdk is a dangling pointer...
- main issue is that SIGWINCH_HANDLER is currently undefined behavior by C standard although it partially works, will fix in future

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
