#pragma once
#include "Entity.h"

enum BlockType { LADRILLO, SORPRESA, VACIO, OCULTO };
enum BlockAction { POTENCIADOR, MONEDA };

class Block : Entity
{
	BlockType type;
	BlockAction action;
};