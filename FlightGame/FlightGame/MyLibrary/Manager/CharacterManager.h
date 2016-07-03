#ifndef OKA_CHARACTERMANAGER_H_
#define OKA_CHARACTERMANAGER_H_

#include<list>
#include"../../Singleton/Singleton.h"
#include"../../Character/Character.h"
#include"../../Character/Player.h"

namespace oka
{
	class CharacterManager : public Singleton<CharacterManager>
	{
		friend class Singleton<CharacterManager>;

	public:
		unsigned int m_flame;
		static const unsigned int m_maxEnemyNum;

		PlayerSP m_player;
		std::list<CharacterSP> m_characters;

		virtual void Update()override;
		void SetPlayer(PlayerSP _player);
		void AddCharacter(CharacterSP _character);
		void CheckPlayer();
		void CheckCharacters();
		void Respawn();

		CharacterManager();
		~CharacterManager();

	private:
		static CharacterManager* m_instance;

	};

}//namespace oka

#endif