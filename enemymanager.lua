function Enemy(t)
	local weapon = t.weapon
	regenemy(t.name,function ()
						return weapon
					end
			)
end
