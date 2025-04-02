#pragma once

//Compatible Exanima Version:
#define version "0.9.0"

//Values:
#define maxhealth 0x3E8000003E800000 // The first 4 bytes is the max health, but I'm repeating it for the purpose of writing in two places at once with one function call.

//Addresses:
#define player_entity 0x0071E7B4
#define health_offset 0xB30 // The max health offset directly follows this (by four bytes).
