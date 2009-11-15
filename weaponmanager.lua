function Weapon(t)
	local w = regweapon(t.righthand[1],t.righthand[2],
						t.lefthand[1],t.lefthand[2],
						t.name,t.firerate,
						t.tip[1],t.tip[2])
	regfirefunction(w,t.whenfire)
	for i = 1, #t.sprite do
		regspriteline(w,t.sprite[i][1],t.sprite[i][2],t.sprite[i][3],t.sprite[i][4])
	end
	return t
end

function Line(t)
	return t
end

function Shot(t)
	if t.gravity == nil then
		t.gravity = 0
	end
	createshot(t.x,t.y,t.angle,t.duration,t.weapon,t.gravity)
end
