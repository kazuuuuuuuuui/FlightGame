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

		virtual void Update()override;
		void SetPlayer(PlayerSP _player);
		PlayerSP GetPlayer()const;
		void AddCharacter(CharacterSP _character);
		std::list<CharacterSP>* GetCharacters();
		void CheckPlayer();
		void CheckCharacters();
		void Respawn();

		CharacterManager();
		~CharacterManager();

	private:
		static CharacterManager* m_instance;
		PlayerSP m_player;
		std::list<CharacterSP> m_characters;
	};

}//namespace oka

#endif