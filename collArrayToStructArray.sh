sed -i -e 's/^const.*\]/CollisionTileRowDbl collisionWide[32]/' $1
sed -i -e 's/0x000//g' $1
# finish this
