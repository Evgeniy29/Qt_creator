#pragma once

#include <QString>
#include <optional>
#include <tuple>

class Symb
{
public:
    Symb() = default;
    std::optional<std::tuple<QString, int, int>> Get_Spec(const QString& line) const;
    QString Spec(const QString& line, const std::tuple<QString, int, int>&spec) const;
};

