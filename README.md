# UCSDVLSIFloorplanning
UCSD VLSI floorplanning project

## Introduction
__*Work in progress*__

## Getting Started
### Setup
#### Cloning repro
__*Work in progress*__

#### Prerequisits
1. Bazel
 
2. Doxygen

## Building
### Floorplan binary
```
bazel build //floorplan:Floorplan
```
### Tests
1. Representation tests
```
bazel build //tests:rep_tests
bazel test //tests:rep_tests
bazel test //tests:rep_tests --verbose_failures
```
