local w = 1600
local h = 1600

local platforms = {
		platform{0,h-200,w,h-200,passable = false},
		platform{0,h,w,h,passable=false}
}

function addPlat(plat)
	platforms[#platforms+1] = platform(plat)
end

local platW = 160
local platH = 50
local platSize = 80

for x = 0, 4 do
	for y = 1, 50 do
		--addPlat({x*platW,h-200-y*platH,platSize+x*platW,h-200-y*platH})
	end
end

for x = 0, 4 do
	for y = 1, 50 do
		--addPlat({platSize+5+x*platW,h-175-y*platH,platSize+platSize+x*platW-5,h-175-y*platH})
	end
end

addPlat {200,h-215,298,h-290,passable=false}
addPlat {500,h-200,500,h-400,passable=false}
addPlat {600,h-300,700,h-300}

map {
	spawn = {400,h-200},
	width = w,
	height = h,
	platforms = platforms,
	weapons = {
		--{name="Flamethrower", spawn={500, h-200}},
		--{name="Shotgun", spawn={300, h-200}},		
	},
	enemies = {
		--{name = "Soldier", spawn={700, h-200}},
	},
}
