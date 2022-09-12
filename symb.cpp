#include "symb.h"

#include <QHash>

namespace
{
QHash<QString, QString> hexHash
    {
            {"#@PRO@", u8"\u2030"},
            {"#@P@",   u8"\u2117"},
            {"#@EUR@", u8"\u20AC"},
            {"#@C@",   u8"\u00A9"},
            {"#@POU@", u8"\u00A3"},
            {"#@R@",   u8"\u00AE"},
            {"#@RUB@", u8"\u20BD"},


    };
}

std::optional<std::tuple<QString, int, int>> Symb::Get_Spec(const QString& line) const
{
    QHash<QString, QString>::const_iterator i = hexHash.constBegin();
    while (i != hexHash.constEnd())
    {
        if(int index = line.indexOf(i.key()); index != -1)
        {
            return std::make_tuple(i.value(), index, i.key().length());
        }
        ++i;
    }
    return std::nullopt;
}

QString Symb::Spec(const QString& line, const std::tuple<QString, int, int>& spec) const
{
    QString formattedText {line};
    const auto& [lexeme, pos, length] = spec;

    formattedText.replace(pos, length, lexeme);
    return formattedText;
}
