#ifndef CARDS_HPP
#define CARDS_HPP

#include "common.hpp"

namespace ck_Cards {

    enum class Cards : uint32_t { //todo: all cards
        BLUE_0 = 0,
        BLUE_1_A = 1,
        BLUE_2_A = 2,
        BLUE_3_A = 3,
        BLUE_4_A = 4,
        BLUE_5_A = 5,
        BLUE_6_A = 6,
        BLUE_7_A = 7,
        BLUE_8_A = 8,
	    BLUE_9_A = 9,
        BLUE_1_B = 10,
        BLUE_2_B = 11,
        BLUE_3_B = 12,
        BLUE_4_B = 13,
        BLUE_5_B = 14,
        BLUE_6_B = 15,
        BLUE_7_B = 16,
        BLUE_8_B = 17,
        BLUE_9_B = 18,
        YELLOW_0 = 19,
        YELLOW_1_A = 20,
        YELLOW_2_A = 21,
        YELLOW_3_A = 22,
        YELLOW_4_A = 23,
        YELLOW_5_A = 24,
        YELLOW_6_A = 25,
        YELLOW_7_A = 26,
        YELLOW_8_A = 27,
        YELLOW_9_A = 28,
        YELLOW_1_B = 29,
        YELLOW_2_B = 30,
        YELLOW_3_B = 31,
        YELLOW_4_B = 32,
        YELLOW_5_B = 33,
        YELLOW_6_B = 34,
        YELLOW_7_B = 35,
        YELLOW_8_B = 36,
        YELLOW_9_B = 37,
	    GREEN_0 = 38,
        GREEN_1_A = 39,
        GREEN_2_A = 40,
        GREEN_3_A = 41,
        GREEN_4_A = 42,
        GREEN_5_A = 43,
        GREEN_6_A = 44,
        GREEN_7_A = 45,
        GREEN_8_A = 46,
        GREEN_9_A = 47,
	    GREEN_1_B = 48,
        GREEN_2_B = 49,
        GREEN_3_B = 50,
        GREEN_4_B = 51,
        GREEN_5_B = 52,
        GREEN_6_B = 53,
        GREEN_7_B = 54,
        GREEN_8_B = 55,
        GREEN_9_B = 56,
	    RED_0 = 57,
        RED_1_A = 58,
        RED_2_A = 59,
        RED_3_A = 60,
        RED_4_A = 61,
        RED_5_A = 62,
        RED_6_A = 63,
        RED_7_A = 64,
        RED_8_A = 65,
        RED_9_A = 66,
        RED_1_B = 67,
        RED_2_B = 68,
        RED_3_B = 69,
        RED_4_B = 70,
        RED_5_B = 71,
        RED_6_B = 72,
        RED_7_B = 73,
        RED_8_B = 74,
        RED_9_B = 75,
	BLUE_SKIP_A = 76,
	BLUE_SKIP_B = 77,
	YELLOW_SKIP_A = 78,
	YELLOW_SKIP_B = 79,
	GREEN_SKIP_A = 80,
	GREEN_SKIP_B = 81,
	RED_SKIP_A =  82,
	RED_SKIP_B = 83,
	BLUE_REVERSE_A = 84,
	BLUE_REVERSE_B = 85,
	YELLOW_REVERSE_A = 86,
	YELLOW_REVERSE_B = 87,
	GREEN_REVERSE_A = 88,
	GREEN_REVERSE_B = 89,
	RED_REVERSE_A = 90,
	RED_REVERSE_B = 91,
	BLUE_DRAW2_A = 92,
	BLUE_DRAW2_B = 93,
	YELLOW_DRAW2_A = 94,
	YELLOW_DRAW2_B = 95,
	GREEN_DRAW2_A = 96,
	GREEN_DRAW2_B = 97,
	RED_DRAW2_A = 98,
	RED_DRAW2_B = 99,
	WILD_A = 100,
	WILD_B = 101,
	WILD_C = 102,
	WILD_D = 103,
	WILD_DRAW4_A = 104,
	WILD_DRAW4_B = 105,
	WILD_DRAW4_C = 106,
	WILD_DRAW4_D = 107
};
    //to iterate over enum
    Cards& operator++ (Cards& it);

    enum class Color : uint32_t {
        GREEN   =   0,
        RED     =   1,
        YELLOW  =   2,
        BLUE    =   3,
	    NONE 	=   4 //for wild cards
    };

    std::string get_color_as_string(const Color& color);

    enum class Value : uint32_t {
	ZERO = 0,
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	NONE = 10//for action_cards
    };

    enum class Action : uint32_t {
	REVERSE = 0,
	SKIP = 1,
	DRAW2 = 2,
	WILD = 3,	
	WILD_DRAW4 = 4,
	NONE = 5
    };

    struct Card {
        Card(Cards _id, Color _col, Value _val, Action _act) : id(_id), color(_col), value(_val), action(_act) {}
        const Cards id;
        const Color color;
	    const Value value;
	    const Action action;
	    std::string get_color_as_string() const;
	    std::string get_action_as_string() const;
	    std::string get_value_as_string() const;
    };

    class Deck {
        const std::unordered_map<Cards, std::unique_ptr<Card>> cards;

        template<class Func>
        Deck(Func _vals) noexcept : cards(_vals()) {}

        static Deck* instance;
    public:
        [[nodiscard]] static const Card& get(Cards /*_card*/) noexcept;
        [[nodiscard]] static const std::vector<std::reference_wrapper<Card>> getByColor(Color /*_color*/) noexcept;
    };


    class Pile {
    protected:
        std::list<Cards> cards;
    public:
        [[nodiscard]] const Cards get_top_card();
        const Cards back();
	    const Cards front();
        void pop();
        void push_front(Cards /*_card*/);
        void push(Cards /*_card*/) noexcept;
        void put_at_end(Cards /*_card*/) noexcept;
        void push(const std::list<Cards> /*cards*/) noexcept;
        void remove(const ck_Cards::Cards /*card*/);
        void shuffle() noexcept;
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        void clear() noexcept;
        Pile(std::list<Cards> /*cards_*/); //constructor
        Pile(); //default constructor
        const std::list<Cards> get_cards() const;
    };

    typedef Pile Draw_Pile;
    typedef Pile Discard_Pile;
    typedef Pile Hand;
}

#endif /*CARDS_HPP*/
