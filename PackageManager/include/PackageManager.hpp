#pragma once

#include <QByteArray>
#include <QDebug>

typedef int32_t INT32;

namespace PackageManager
{
	void int32_Paketle(QByteArray *byteArray, INT32 value)
	{
		byteArray->append((char *)&value, sizeof(INT32));
	};
}