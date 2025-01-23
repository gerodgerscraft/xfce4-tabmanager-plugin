# XFCE4 Tab Manager Plugin

A plugin for the XFCE4 panel that provides enhanced tab management functionality with a full-length vertical indicator bar.

## Features

- Full-length vertical indicator bar (10px wide, 900px high)
- Indicator bar matches active application color
- Remains visible even when taskbar is hidden
- Integrates with XFCE theme system

## Dependencies

- GTK+ 3.0
- libxfce4panel-2.0
- libxfce4ui-2
- libxfce4util

## Building from Source

1. Install build dependencies:
```bash
sudo apt install build-essential autoconf automake libtool pkg-config \
                 libgtk-3-dev libxfce4panel-2.0-dev libxfce4ui-2-dev \
                 libxfce4util-dev xfce4-dev-tools
```

2. Generate build system:
```bash
./autogen.sh
```

3. Configure and build:
```bash
./configure
make
```

4. Install:
```bash
sudo make install
```

## License

This project is licensed under the GNU General Public License v2 or later.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. 
