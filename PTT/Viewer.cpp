#include "Viewer.h"
#include "BoardManager.h"

Viewer::~Viewer()
{
	cout << CSI "J";
}
