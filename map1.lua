local w = 800
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
		addPlat({x*platW,h-200-y*platH,platSize+x*platW,h-200-y*platH})
	end
end

for x = 0, 4 do
	for y = 1, 50 do
		addPlat({platSize+5+x*platW,h-175-y*platH,platSize+platSize+x*platW-5,h-175-y*platH})
	end
end

map {
	spawn = {400,h-200},
	width = w,
	height = h,
	platforms = platforms,
	weapons = {
		{name="Flamethrower", spawn={485, 100}}
	},
}
