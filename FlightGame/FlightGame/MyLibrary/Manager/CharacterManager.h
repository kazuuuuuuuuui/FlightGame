#ifndef OKA_CHARACTERMANAGER_H_
#define OKA_CHARACTERMANAGER_H_

#include<vector>
#include"../../Character/Character.h"

namespace oka
{
	class CharacterManager
	{
	public:
		std::vector<Character*> m_characters;

		void Update();
		static CharacterManager* GetInstance();
		void AddCharacter(Character *_character);
		void CheckCharacter();
		static void Destroy();

		CharacterManager();

		~CharacterManager();

	private:
		static CharacterManager* m_instance;

	};

}//namespace oka

#endif