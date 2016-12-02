#pragma once
#include "gameNode.h"
#include "animation.h"

class animTest :public gameNode
{
private:
	image* _camel;
	image* _camel2;
	image* _camel3;

	animation* _ani;
	animation* _ani2;
	animation* _ani3;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	animTest();
	~animTest();
};

