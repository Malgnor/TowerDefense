#include "Ator.h"

Ator::Ator(GerenteAtor& _gerente, int _layer)
	: gerente(_gerente), layer(_layer)
{
}

bool Ator::operator>( Ator& ator )
{
	return this->layer > ator.layer;
}
