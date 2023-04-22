# mbed_pid-example
An example of using the 6TRON PID library with MbedOS.

## Requirements
### Hardware requirements
The following boards are required:
- *List mbed_pid-example hardware requirements here*

### Software requirements
mbed_pid-example makes use of the following libraries (automatically
imported by `mbed deploy` or `mbed import`):
- *List mbed_pid-example software requirements here*

## Usage
To clone **and** deploy the project in one command, use `mbed import` and skip to the
target and toolchain definition:
```shell
mbed import https://gitlab.com/catie_6tron/mbed_pid-example.git mbed_pid-example
```

Alternatively:

- Clone to "mbed_pid-example" and enter it:
  ```shell
  git clone https://gitlab.com/catie_6tron/mbed_pid-example.git mbed_pid-example
  cd mbed_pid-example
  ```

- Deploy software requirements with:
  ```shell
  mbed deploy
  ```

- Clone custom target repository if necessary:
  ```shell
  git clone YOUR_CUSTOM_TARGET_REPOSITORY your-custom-target
  ```

Define your target and toolchain:
```shell
cp your-custom-target/custom_targets.json . # In case of custom target
mbed target YOUR_MBED_OS_TARGET
mbed toolchain GCC_ARM
```

Compile the project:
```shell
mbed compile
```

Program the target device with a Segger J-Link debug probe and
[`sixtron_flash`](https://gitlab.com/catie_6tron/6tron-flash) tool:
```shell
sixtron_flash YOUR_JLINK_DEVICE BUILD/YOUR_MBED_OS_TARGET/GCC_ARM/mbed_pid-example.elf
```

Debug on the target device with the probe and Segger
[Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger)
software.
