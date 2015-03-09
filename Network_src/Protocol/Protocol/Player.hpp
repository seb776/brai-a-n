#pragma once

# include <vector>
# include "TerrariaInfo.hpp"

class Player
{
private:
	bool				logged;
	bool				playing;
	uint8				slot;
	std::vector<ItemId>	inventory;

public:

	Player();
	Player(const Player&) = default;

	void	setSlot(uint8 newVal);
	uint8	getSlot() const;

	void	setLogged(bool status);
	bool	isLogged() const;

	void	setPlaying(bool status);
	bool	isPlaying() const;

	const std::vector<ItemId>&	getInventory();
};