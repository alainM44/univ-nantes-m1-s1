#!/bin/bash

echo 'compil server';
gcc -o server server.c  common/network.c common/gestion_menu.c  -std=gnu99;
echo 'compil client';
gcc -o client client.c  common/network.c common/gestion_menu.c  -std=gnu99

