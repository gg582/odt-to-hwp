# ODT to Hancom Converter

An Electron desktop application that converts OpenDocument Text (`.odt`) files to Hancom HWP (`.hwp`) or Hancom HWPX (`.hwpx`) formats using the [`HwpCtrl.SaveAs`](https://developer.hancom.com/webhwp/devguide/hwpctrl/methods/saveas) automation API.

## Prerequisites

- Windows environment with Hancom Office installed (required for the automation control)
- Node.js 18+
- On Windows, install the optional [`winax`](https://www.npmjs.com/package/winax) dependency (automatically attempted during install)

## Getting Started

```bash
npm install
npm start
```

`npm start` launches the Electron UI, allowing you to select an ODT file and convert it to either `.hwp` or `.hwpx` formats.

## Building

Run the build script to create a distributable directory using `electron-builder`:

```bash
npm run build
```

The build output will be written to the `dist/` directory.

## How It Works

- The renderer process collects the user's input (source ODT and desired output format).
- The main process forwards conversion requests to the Node backend.
- The backend uses `winax` to automate the Hancom HWP ActiveX control (`HWPFrame.HwpObject`) and invokes `SaveAs` with the requested format.
