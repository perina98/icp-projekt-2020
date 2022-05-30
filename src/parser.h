/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#ifndef PARSER_H
#define PARSER_H

#include "stop.h"
#include "line.h"
#include "street.h"

#include "QString"
#include "QFile"

#include <iostream>
#include <map>

//! Class representig parser used for parsing input examples
class Parser
{
public:
    Parser();
    std::vector<Street*> parseRoads(QString fileName);
    std::vector<Stop*> parseStops(QString fileName);
    std::vector<Line*> parseLines(QString fileName);
};

#endif // PARSER_H
