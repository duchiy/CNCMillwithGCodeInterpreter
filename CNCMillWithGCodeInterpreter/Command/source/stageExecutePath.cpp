#include "stdafx.h"
#include "stageExecutePath.h"

stageExecutePath::stageExecutePath(Stage & stage, Path & path):_stage(stage), _path(path)
{
};
int stageExecutePath::execute()
{
	_stage.ExecuteCoordMotion(_path);
	return 0;
};

