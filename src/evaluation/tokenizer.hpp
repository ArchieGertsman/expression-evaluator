#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

/**
 * The Tokenizer class takes in all the strokes that the user has sketched and
 * uses them to segment the sketch into all of the expression's individual tokens
 *
 * Sources:
 * https://bit.ly/2L3DT92
 * https://bit.ly/2PsCnxJ
 * https://bit.ly/2GaU7hS
 * https://bit.ly/2EcCcEN
 * https://bit.ly/2QrXOVf
 **/

#include "stroke-combination.hpp"
#include <QSize>
#include <vector>
#include <cstddef>

namespace expression_evaluator { namespace eval {


using ui::Stroke;


class Tokenizer {
private:    // static constants

    static const double kConfidenceThreshold;


public:     // c-tors

    Tokenizer(const std::vector<Stroke> &strokes_list, const QSize &img_size);


private:    // private methods

    void constructStrokeCombinations();

    std::vector<bool> constructBitVector(std::size_t combination_size) const;

    StrokeCombination getStrokeCombinationIndicatedByBitVector(
            const std::vector<bool> &) const;

    void saveCombination(const StrokeCombination &, const std::vector<bool> &);


public:     // getters

    std::vector<char> getTokens() const { return tokens_; }


private:    // member constants & variables

    std::vector<char> tokens_;

    std::vector<Stroke> strokes_list_;

    const QSize img_size_;

    std::vector<StrokeCombination> stroke_combinations_;

};


} }

#endif // TOKENIZER_HPP
