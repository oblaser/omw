#!/bin/bash

# author        Oliver Blaser
# date          17.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

cd cmake
./omw-system-test-cli-shared
./omw-system-test-cli-static
./omw-unit-test-shared
./omw-unit-test-static
