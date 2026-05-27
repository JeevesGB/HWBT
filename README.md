# HWBT — Hot Wheels: Beat That! Reverse Engineering

A reverse engineering project for **Hot Wheels: Beat That!** (PC), documenting file formats, game structures, and recreated assets.

---

## 📁 Repository Structure

```
HWBT/
├── GameFiles/          # Original game files (not tracked in git)
├── Ghidra/             # Ghidra project for executable analysis
│   └── HotwheelsBeatThatPC.rep/
│       └── versioned/  # Tracked: function names, comments, annotations
├── Recreated/          # Recreated/decompiled source files
│   ├── c/              # Reconstructed C code
│   └── readable files/ # Human-readable format documentation
├── Text/               # Text dumps and function lists
│   └── funcs.txt       # Named/identified functions
├── VSCode-Extensions/  # Syntax highlighting extensions for custom formats
│   ├── hwbt-syntax-1.0.0.vsix
│   └── hwbt-syntax-1.1.0.vsix
└── hwbt.html           # WIP Webpage based editor
```

---

## 🔧 Tools Used

- **[Ghidra](https://ghidra-sre.org/)** — NSA reverse engineering suite, used for disassembly and decompilation of the game executable
- **[VSCode](https://code.visualstudio.com/)** — with custom syntax extensions (included) for game-specific file formats

---

## 📦 Known File Formats

| Extension | Description |
|-----------|-------------|
| `.LAS` | Zone/level audio or script data |
| `.LS` | Script files (e.g. battle stock, zone objectives) |
| `.AMM` | AI driver/behaviour data |
| `.EPD` | Eliminator game mode data |
| `.GCF` | Game configuration |
| `.UCP` | Garage/vehicle unlock/config data |
| `.MOV` | Video/cutscene |
| `.PTL` | Particle effects |
| `.CUT` | Tournament results cutscene data |
| `.TES` | Zone terrain or event script |
| `.VEH` | Vehicle definition |
| `.CMS` | Commentary strings |
| `.dat` | Generic binary data |

---

## 🚀 Getting Started

### Viewing Ghidra Analysis

1. Install [Ghidra](https://ghidra-sre.org/)
2. Open Ghidra and select **File → Open Project**
3. Navigate to `Ghidra/` and open `HotwheelsBeatThatPC.gpr`
4. The project contains annotated functions, renamed variables, and comments

### Installing the VSCode Syntax Extension

1. Open VSCode
2. Press `Ctrl+Shift+P` → **Extensions: Install from VSIX...**
3. Select `VSCode-Extensions/hwbt-syntax-1.1.0.vsix`

---

## ⚠️ Legal Notice

This project is for **educational and research purposes only**. No copyrighted game assets are included in this repository. You must own a legitimate copy of *Hot Wheels: Beat That!* to make use of any tooling or documentation here.

---

## 🤝 Contributing

Findings, format documentation, and annotated function names are welcome. Please open an issue or PR with any corrections or additions.