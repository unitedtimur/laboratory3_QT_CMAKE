#pragma once

#include "include/AbstractStrategy.h"
#include <QDir>

/*
 * Forward declaration
 */
class QTextStream;
class QPieSeries;

class FolderGrouping final : public AbstractStrategy
{
public:
	explicit FolderGrouping();
	virtual ~FolderGrouping() override;
	void* explorer(const QString& path) override;

private:

	struct TotalSize
	{
		explicit TotalSize() { size = 0; }

		quint64 get(const QString& path) noexcept
		{
			for (const auto& it : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
				(it.isDir() /*&& !it.isSymLink()*/) ? TotalSize::get(it.absoluteFilePath()) : size += it.size();

			return size;
		}

	private:
		quint64 size;
	};

	quint64 totalSize(const QString& path) noexcept;

private:
	QTextStream* cin;
	QTextStream* cout;
	QPieSeries* pie;
};