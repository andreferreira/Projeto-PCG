local x = 1024
local y = 32768

map {
	spawn = {x/2, y-250},
	width = x,
	height = y,
	platforms = {
		platform{0, y-250, x, y-250, passable = false},
	},
	weapons = {
		{name = "Flamethrower", spawn = {x/3, y-5000}},
	},
	enemies = {
		{name = "Soldier", spawn = {2*x/3, y-15000}},
		{name = "Soldier", spawn = {2*x/3, y-250}},
	},
}
