function Weapon(t)
	local w = regweapon(t.righthand[1],t.righthand[2],
						t.lefthand[1],t.lefthand[2],
						t.name)
	for i = 1, #t.sprite do
		regspriteline(w,t.sprite[i][1],t.sprite[i][2],t.sprite[i][3],t.sprite[i][4])
	end
	return t
end

function Line(t)
	return t
end
