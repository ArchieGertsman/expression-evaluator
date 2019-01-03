#include "tokenizer.hpp"

#include <QSize>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstddef>

namespace expression_evaluator { namespace eval {


/* static const variables */

const double Tokenizer::kConfidenceThreshold = -0.05;


/* c-tors */

Tokenizer::Tokenizer(
        const std::vector<Stroke> &strokes_list,
        const QSize &img_size) :
    strokes_list_(strokes_list),
    img_size_(img_size)
{
    this->constructStrokeCombinations();

    std::sort(std::begin(stroke_combinations_), std::end(stroke_combinations_));

    std::transform(std::begin(stroke_combinations_),
                   std::end(stroke_combinations_),
                   std::back_inserter(tokens_),
                   [] (const StrokeCombination &sc) {
                        return sc.getPrediction();
                   });
}


/* methods */

void Tokenizer::constructStrokeCombinations() {
    for (auto combination_size = strokes_list_.size();
         combination_size > 0;
         --combination_size)
    {
        auto bit_vector = this->constructBitVector(combination_size);

        do {
            const auto &stroke_combination =
                    this->getStrokeCombinationIndicatedByBitVector(bit_vector);

            if (stroke_combination.getConfidence() >= kConfidenceThreshold) {
                this->saveCombination(stroke_combination, bit_vector);

                combination_size = strokes_list_.size() + 1;
                break;
            }

        } while (std::next_permutation(std::begin(bit_vector), std::end(bit_vector)));
    }
}


std::vector<bool> Tokenizer::constructBitVector(
        std::size_t combination_size) const
{
    std::vector<bool> bit_vector(strokes_list_.size());

    std::fill(
        std::end(bit_vector) - static_cast<int>(combination_size),
        std::end(bit_vector), true);

    return bit_vector;
}


StrokeCombination Tokenizer::getStrokeCombinationIndicatedByBitVector(
        const std::vector<bool> &bit_vector) const
{
    std::vector<Stroke> strokes;

    for (std::size_t i = 0; i < strokes_list_.size(); ++i) {
        if (bit_vector[i]) {
            strokes.push_back(strokes_list_[i]);
        }
    }

    return StrokeCombination(strokes, img_size_);
}


void Tokenizer::saveCombination(
        const StrokeCombination &comb,
        const std::vector<bool> &bit_vector)
{
    std::vector<std::size_t> indices_to_remove;

    for (std::size_t i = 0; i < bit_vector.size(); ++i) {
        if (bit_vector[i]) {
            indices_to_remove.push_back(i);
        }
    }

    stroke_combinations_.push_back(comb);

    for (const auto &i : indices_to_remove) {
        strokes_list_[i] = strokes_list_.back();
        strokes_list_.pop_back();
    }
}


} }
