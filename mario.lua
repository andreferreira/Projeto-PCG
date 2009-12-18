local x = 10000
local y = 1000

map {
	spawn = {150, y-250},
	width = x,
	height = y,
	platforms = {
		platform{0,    y,     0,    y-250, color = {0.5, 0.5, 0}, passable = false},
		platform{0,    y-250, 650,  y-250, color = {0.5, 0.5, 0}, passable = false},
		platform{650,  y,     650,  y-250, color = {0.5, 0.5, 0}, passable = false},

		platform{150,  y-350, 350,  y-350, color = {0.5, 0.5, 0}},

		platform{100,  y-450, 250,  y-450, color = {0.5, 0.5, 0}},

		platform{150,  y-550, 300,  y-550, color = {0.5, 0.5, 0}},

		platform{250,  y-650, 450,  y-650, color = {0.5, 0.5, 0}},

		platform{600,  y-600, 750,  y-600, color = {0.5, 0.5, 0}},

		-- primeiro "balanço" 
		platform{900,  y-550, 1050, y-550, color = {0.5, 0.25, 0}},

		platform{1200, y,     1200, y-449, color = {0.5, 0.5, 0}, passable = false},
		platform{1200, y-450, 1500, y-450, color = {0.5, 0.5, 0}, passable = false},
		platform{1500, y,     1500, y-449, color = {0.5, 0.5, 0}, passable = false},

		platform{1550, y-550, 1700, y-550, color = {1, 1, 0}},

		platform{1750, y-650, 1900, y-650, color = {1, 1, 0}},

		platform{1900, y,     1900, y-249, color = {0.5, 0.5, 0}, passable = false},
		platform{1900, y-250, 2250, y-250, color = {0.5, 0.5, 0}, passable = false},
		platform{2250, y,     2250, y-249, color = {0.5, 0.5, 0}, passable = false},

		platform{2000, y-650, 2150, y-650, color = {0.5, 0.5, 0}},

		platform{2300, y-600, 2450, y-600, color = {0.5, 0.25, 0}},

		platform{2600, y,     2600, y-549, color = {0.5, 0.5, 0}, passable = false},
		platform{2600, y-550, 2750, y-550, color = {0.5, 0.5, 0}, passable = false},
		platform{2750, y,     2750, y-549, color = {0.5, 0.5, 0}, passable = false},

		platform{2900, y-550, 3050, y-550, color = {0.5, 0.5, 0.5}},

		platform{3100, y-550, 3250, y-550, color = {0.5, 0.5, 0.5}},

		platform{3300, y-650, 3600, y-650, color = {0.5, 0.5, 0}},

		platform{3750, y-550, 3900, y-550, color = {0.5, 0.25, 0}},

		platform{4050, y-450, 4200, y-450, color = {0.5, 0.25, 0}},

		platform{4200, y,     4200, y-349, color = {0.5, 0.5, 0}, passable = false},
		platform{4200, y-350, 4500, y-350, color = {0.5, 0.5, 0}, passable = false},
		platform{4500, y-250, 4500, y-349, color = {0.5, 0.5, 0}, passable = false},
		platform{4500, y-250, 5500, y-250, color = {0.5, 0.5, 0}, passable = false},
		platform{5500, y-250, 5500, y-449, color = {0.5, 0.5, 0}, passable = false},
		platform{5500, y-450, 5650, y-450, color = {0.5, 0.5, 0}, passable = false},
		platform{5650, y,     5650, y-449, color = {0.5, 0.5, 0}, passable = false},

		platform{5300, y-350, 5450, y-350, color = {1, 1, 0}},

		platform{5700, y-550, 5850, y-550, color = {0.5, 0.5, 0.5}},

		platform{5900, y-650, 6050, y-650, color = {0.5, 0.5, 0}},

		platform{6200, y-550, 6350, y-550, color = {0.5, 0.25, 0}},

		platform{6500, y-350, 6650, y-350, color = {1, 1, 0}},

		platform{6650, y-450, 6950, y-450, color = {1, 1, 0}},

		platform{6950, y-550, 7250, y-550, color = {1, 1, 0}},

		platform{7250, y-650, 7350, y-650, color = {1, 1, 0}},

		platform{7350, y,     7350, y-750, color = {0.5, 0.5, 0}, passable = false},
		platform{7350, y-750, 7500, y-750, color = {0.5, 0.5, 0}, passable = false},
		platform{7500, y,     7500, y-750, color = {0.5, 0.5, 0}, passable = false},

		platform{7650, y-650, 7800, y-650, color = {0.5, 0.5, 0.5}},

		platform{7900, y-600, 8050, y-600, color = {0.5, 0.25, 0}},

		platform{8150, y-650, 8300, y-650, color = {0.5, 0.5, 0}},

		platform{8450, y-600, 8600, y-600, color = {0.5, 0.25, 0}},

		platform{8750, y-550, 8900, y-550, color = {0.5, 0.25, 0}},

		platform{9000, y,     9000, y-500, color = {0.5, 0.5, 0}, passable = false},
		platform{9000, y-500, 9200, y-500, color = {0.5, 0.5, 0}, passable = false},
		platform{9200, y-400, 9200, y-499, color = {0.5, 0.5, 0}, passable = false},
		platform{9200, y-400, 9400, y-400, color = {0.5, 0.5, 0}, passable = false},
		platform{9400, y-300, 9400, y-399, color = {0.5, 0.5, 0}, passable = false},
		platform{9400, y-300, 9999, y-300, color = {0.5, 0.5, 0}, passable = false},
		platform{9999, y,     9999, y-300, color = {0.5, 0.5, 0}, passable = false},
	},
	weapons = {
		{name = "Flamethrower", spawn = {5400, y-400}},
	},
	enemies = {
		{name = "Soldier", spawn = {750, y-750}},
		{name = "Pyro", spawn = {1500, y-750}},
		{name = "Soldier", spawn = {2250, y-750}},
		{name = "Soldier", spawn = {3000, y-750}},
		{name = "Soldier", spawn = {3750, y-750}},
		{name = "Pyro", spawn = {4500, y-750}},
		{name = "Soldier", spawn = {5250, y-750}},
		{name = "Soldier", spawn = {6000, y-750}},
		{name = "Bear", spawn = {9500, y-500}},
	},
}
