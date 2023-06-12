#include "deck_manager.hpp"

#include <codecvt>
#include <random>

using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}


/*!
* @brief Класс изучения карточек
* 
* Позволяет проводить сам квиз - 
* устанавливать текущую колоду, получать случайную карточку,
* проверять пользовательский ответ и т.д.
*/
class QuizManager {
private:
  DeckManager cards;
  std::string deck_id_{ "0" };
  CardsContainer study_deck_{ cards.GetShuffledDeck(deck_id_) };
  Flashcard current_card_;

public:

  /*!
  * @brief Конструктор по умолчанию
  */
  QuizManager(); 

  /*!
  * @brief Конструктор по идентификатору колоды
  * 
  * Создаёт экземпляр класса, в котором данная
  * колода является текущей
  * 
  * @param deck_id Идентификатор колоды
  */
  QuizManager(std::string& deck_id);

  /*!
  * @brief Деструктор по умолчанию
  */
  ~QuizManager();
  
  /*!
  * @brief Устанавливает текущую колоду
  * 
  * Устанавливает в качестве текущей колоду,
  * соответствующую данному идентификатору
  * 
  * @param deck_id Идентификатор колоды
  */
  void SetCurrentDeck(std::string& deck_id);

  /*!
  * @brief Получает размер колоды
  * @return Размер текущей колоды
  */
  const int GetCurrentDeckSize();

  /*!
  * @brief Получает все имеющиеся колоды
  * @return Массив пар из всех колод и их идентификаторов
  */
  const DeckContainer LoadAllDecks();

  /*!
  * @brief Получает идентификатор колоды
  * @return Идентификатор текущей колоды
  */
  const std::string GetCurrentDeckId();

  /*!
  * @brief Получает название колоды
  * @param deck_id Идентификатор колоды
  * @return Название колоды,
  * соответствующей данному идентификатору
  */
  const std::wstring GetDeckNameFromId(std::string& deck_id);

  /*!
  * @brief Получает название колоды
  * @return Название текущей колоды
  */
  const std::wstring GetCurrentDeckName();

  /*!
  * @brief Получает все карточки из колоды
  * @return Все имеющиеся
  * карточки
  */
  const CardsWithId GetCardsList();

  /*!
  * @brief Получает список карточек
  * @param deck_id Идентификатор колоды
  * @return Массив пар вида
  * "Идентификатор карточки - вопрос" из
  * текущей колоды
  */
  const CardsWithId GetCurrentCardsList();

  /*!
  * @brief Получает карточку
  * @return Пару "вопрос - ответ"
  */
  const Flashcard GetCard();

  /*!
  * @brief Получает вопрос
  * @return Вопрос из карточки
  */
  const std::wstring GetQuestion();

  /*!
  * @brief Получает ответ
  * @return Ответ из карточки
  */
  const std::wstring GetAnswer();
  
  /*!
  * @brief Проверяет ответ
  * 
  * Проверяет данный пользователем ответ
  * 
  * @param user_ans Ответ пользователя
  * @param card_ans Ожидаемый ответ из карточки
  * @return True, если ответ пользователя верный, 
  * в противном случае False
  */
  const bool CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans);

  /*!
  * @brief Меняет название колоды
  * @param deck_id Идентификатор колоды
  * @param new_name Новое название колоды
  */
  const void RenameCurrentDeck(const std::string& deck_id, std::wstring& new_name);

  /*!
  * @brief Добавляет карточку в колоду
  * @param card_id Идентификатор карточки
  * @param deck_id Идентификатор колоды
  */
  const void AddToDeck(const int& card_id, std::string& deck_id);
  
  /*!
  * @brief Добавляет карточку в колоду
  * @param card_id Идентификатор карточки
  * @param deck_id Идентификатор колоды
  */
  const void RemoveFromDeck(const int& card_id, std::string& deck_id);

  /// @private
  void EraseCurrentCard();
};