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

## Limitations

- Conversion only works on Windows because Hancom's automation components are Windows-only.
- On non-Windows systems the application UI is disabled and displays guidance on the missing dependencies.

## Usage

### Docker (Web Version)

The web version of the converter can be run inside a Docker container. This is useful for deploying the conversion service on a server.

1.  **Build the Docker image:**

    ```bash
    docker build -t odt-to-hwp .
    ```

2.  **Run the container:**

    ```bash
    docker run -p 3000:3000 odt-to-hwp
    ```

    The web interface will be available at `http://localhost:3000`.

### AppImage (Desktop)

To use the desktop application on Linux, you can build an AppImage.

1.  **Install dependencies:**

    ```bash
    npm install
    ```

2.  **Build the AppImage:**

    The `build` script in `package.json` is configured to create an AppImage when run on Linux.

    ```bash
    npm run build
    ```

    This will generate an AppImage file in the `dist/` directory.

3.  **Run the AppImage:**

    Make the AppImage executable and run it.

    ```bash
    chmod +x dist/*.AppImage
    ./dist/*.AppImage
    ```

### Web Deployment

The `web/` directory contains a standalone version of the application that can be deployed to any static web hosting service.

1.  **Local Testing:**

    To serve the `web` directory locally, you can use the `serve` package.

    ```bash
    npm install -g serve
    serve web
    ```

    The application will be available at `http://localhost:3000` (or another port if 3000 is in use).

2.  **Deployment:**

    For production, upload the contents of the `web/` directory to your preferred static hosting provider (e.g., GitHub Pages, Netlify, Vercel, or your own server).
