#pragma once

enum BlockType { LADRILLO, SORPRESA, VACIO, OCULTO };
enum BlockAction { POTENCIADOR, MONEDA };

class Block
{
	BlockType type;
	BlockAction action;
};