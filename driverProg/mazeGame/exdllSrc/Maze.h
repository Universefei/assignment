enum PositionInfo { 
	Entrance, 
		Exit, 
		Path, 
		Wall 
};

enum Direction { 
	Left, 
		Right, 
		Up, 
		Down 
};

struct Position { 
	int X;
	int Y;
};

struct IMAZE{
	PositionInfo (*GetPositionInfo)(Direction direction);
	Position (*GetEntracePosition)();
	Position (*GetExitPosition)();
	Position (*GetCurrentPosition)();
};