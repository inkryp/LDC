#include "ExpressionChecker.h"
using namespace ldc;

const std::vector<std::vector<std::vector<SupportedType>>>
    ExpressionChecker::semanticCube = {
        {// INT INT
         {SupportedType::INT, SupportedType::INT, SupportedType::INT,
          SupportedType::INT, SupportedType::BOOL, SupportedType::BOOL,
          SupportedType::BOOL},
         // INT FLOAT
         {SupportedType::FLOAT, SupportedType::FLOAT, SupportedType::FLOAT,
          SupportedType::FLOAT, SupportedType::BOOL, SupportedType::BOOL,
          SupportedType::BOOL},
         // INT BOOL
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // INT UNDEFINED
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED}},
        {// FLOAT INT
         {SupportedType::FLOAT, SupportedType::FLOAT, SupportedType::FLOAT,
          SupportedType::FLOAT, SupportedType::BOOL, SupportedType::BOOL,
          SupportedType::BOOL},
         // FLOAT FLOAT
         {SupportedType::FLOAT, SupportedType::FLOAT, SupportedType::FLOAT,
          SupportedType::FLOAT, SupportedType::BOOL, SupportedType::BOOL,
          SupportedType::BOOL},
         // FLOAT BOOL
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // FLOAT UNDEFINED
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED}},
        {// BOOL INT
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // BOOL FLOAT
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // BOOL BOOL
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::BOOL, SupportedType::BOOL, SupportedType::BOOL},
         // BOOL UNDEFINED
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED}},
        {// UNDEFINED INT
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // UNDEFINED FLOAT
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // UNDEFINED BOOL
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED},
         // UNDEFINED UNDEFINED
         {SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED, SupportedType::UNDEFINED,
          SupportedType::UNDEFINED}}};
