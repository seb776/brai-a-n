#include "Player.hpp"

Player::Player() : logged(false), playing(false), slot(0)
{
	inventory.push_back(ItemId::BROADSWORD);
	inventory.push_back(ItemId::PICKAXE);
	inventory.push_back(ItemId::AXE);
	inventory.push_back(ItemId::TORCH);
}

void	Player::setSlot(uint8 newVal)
{
	slot = newVal;
}

uint8	Player::getSlot() const
{
	return slot;
}

void	Player::setLogged(bool status)
{
	logged = status;
}

bool	Player::isLogged() const
{
	return logged;
}

void	Player::setPlaying(bool status)
{
	playing = status;
}

bool	Player::isPlaying() const
{
	return playing;
}

const std::vector<ItemId>&	Player::getInventory()
{
	return inventory;
}