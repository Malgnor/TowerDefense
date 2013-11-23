#include "Ator.h"

Ator::Ator(GerenteAtor& _gerente, int _layer)
	: gerente(_gerente), layer(_layer)
{
}

int Ator::getLayer()
{
	return layer;
}
