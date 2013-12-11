#ifndef _GLOBALDEF_H_
#define _GLOBALDEF_H_

#define DEBUG

#define QTDTORRES 5

//RTF = Ready to fire
enum tEstado { RTF, COOLDOWN };

enum Tipo { TORRE, PROJETIL, INIMIGO, COIN, SCOLISAO };

enum iDirecao { iCIMA, iBAIXO, iESQUERDA, iDIREITA, iPARADO };

enum orientacao {HORIZONTAL, VERTICAL};

enum mToggle { DESATIVADO, ATIVADO };

enum mButton { NAOPRESSIONADO, PRESSIONADO, SOLTO };

enum miEstado { MENU, MAPSELECT };

enum tdEstado { PLAY, PAUSE, PAUSEF1, GAVEOVER, WIN };

enum faseTutorial { INTRO, PRIMEIROSPASSOS, TORRE0, TORRE1, MOEDAS, TORRE2, UPGRADE, VENDER, RTORRE, RMOEDAS, FIM };

#endif