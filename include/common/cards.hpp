#ifndef CARDS_HPP
#define CARDS_HPP

#include "common.hpp"

namespace ck_Cards {

    enum class Cards : uint32_t { //todo: all cards
        TEST_BLUE_4_A       =       0, 
        TEST_BLUE_4_B       =       1, 
        TEST_BLUE_4_C       =       2, 
        TEST_BLUE_4_D       =       3

    };

    enum class Color : uint32_t {
        GREEN   =   0,
        RED     =   1,
        YELLOW  =   2,
        BLUE    =   3,
	NONE 	=   4 //for wild cards
    };

    //TODO: should include action_type for special cards, value
    struct Card {
        Card(Cards _id, Color _col) : id(_id), color(_col){}
        const Cards id;
        const Color color;
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
        [[nodiscard]] Cards top() const;
        void pop();
        void push(Cards /*_card*/) noexcept;
        void push(const std::vector<Cards> /*cards*/) noexcept;      
        void shuffle() noexcept;
        virtual void from_json(const std::string&);
        [[nodiscard]] virtual const std::string to_json() const noexcept;
        [[nodiscard]] bool size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        void clear() noexcept;
        [[nodiscard]] bool valid(Cards /*_card*/) const noexcept;
    };

    typedef Pile Draw_Pile;
    typedef Pile Discard_Pile;
    typedef Pile Hand;
}

#endif /*CARDS_HPP*/
