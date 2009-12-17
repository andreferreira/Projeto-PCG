local w = 8000
local h = 1000

local platforms = {
		platform{0,h-200,w,h-200,passable = false},
		platform{0,h,w,h,passable=false}
}

function addPlat(plat)
	plat[2] = h-plat[2]
	plat[4] = h-plat[4]
	platforms[#platforms+1] = platform(plat)
end

function Enemy(t)
	t.spawn[2] = h-t.spawn[2]
	return t
end

addPlat {400,200,400,1000, passable = false}
addPlat {400,300,800,300}
addPlat {700,200,700,299, passable = false}
addPlat {800,300,800,1000, passable = false}

map {
	spawn = {500,h-200},
	width = w,
	height = h,
	platforms = platforms,
	weapons = {
		--{name="Flamethrower", spawn={500, h-200}},
		--{name="Shotgun", spawn={300, h-200}},		
	},
	enemies = {
		Enemy {name = "Bear", spawn={980, 200}},
		Enemy {name = "Pyro", spawn={530, 15000}},
	},
}
