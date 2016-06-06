#ifndef OKA_CHARACTERMANAGER_H_
#define OKA_CHARACTERMANAGER_H_

#include<list>
#include"../../Character/Character.h"
#include"../../Character/Player.h"

namespace oka
{
	class CharacterManager
	{
	public:
		PlayerSP m_player;
		std::list<CharacterSP> m_characters;

		void Update();
		static CharacterManager* GetInstance();
		void SetPlayer(PlayerSP _player);
		void AddCharacter(CharacterSP _character);
		void CheckPlayer();
		void CheckCharacters();
		static void Destroy();

		CharacterManager();
		~CharacterManager();

	private:
		static CharacterManager* m_instance;

	};

}//namespace oka

#endif