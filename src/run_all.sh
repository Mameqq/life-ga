#!/bin/bash

echo "=== BLINKER ==="
./game_of_life < ../samples/blinker.txt

echo "=== GLIDER ==="
./game_of_life < ../samples/glider.txt

echo "=== BLOCK ==="
./game_of_life < ../samples/block.txt

echo "=== TUB ==="
./game_of_life < ../samples/tub.txt

echo "=== BEACON ==="
./game_of_life < ../samples/beacon.txt