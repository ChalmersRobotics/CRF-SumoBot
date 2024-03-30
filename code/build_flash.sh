#!/usr/bin/env bash

PORT="/dev/ttyUSB0"
FQBN="arduino:avr:nano"
BOARD_OPTIONS="cpu=atmega328"
INO_DIR="sumobot"

arduino-cli core install arduino:avr
arduino-cli lib install HCSR04
arduino-cli compile --upload --fqbn=${FQBN} --port=${PORT} --board-options=${BOARD_OPTIONS} ${INO_DIR}
