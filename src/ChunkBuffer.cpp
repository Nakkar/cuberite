
#include "Globals.h"
#include "ChunkBuffer.h"

cChunkBuffer cChunkBuffer::Copy() const
{
	cChunkBuffer copy;
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		if(m_Sections[i])
		{
			copy.m_Sections[i] = Allocate();
			*copy.m_Sections[i] = *m_Sections[i];
		}
	}
	return copy;
}





void cChunkBuffer::CopyBlocks   (BLOCKTYPE * a_dest, size_t a_Idx, size_t length)  const
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length =  CHUNK_SECTION_HEIGHT * 16 * 16;
		if (a_Idx > 0) a_Idx = a_Idx > length ? a_Idx - length : 0;
		if (a_Idx == 0) 
		{
			size_t tocopy = length > segment_length ? segment_length : length;
			length -= tocopy;
			memcpy(&a_dest[i * segment_length], &m_Sections[i]->m_BlockTypes, sizeof(BLOCKTYPE) * length);
		}
	}
}





void cChunkBuffer::CopyMeta(NIBBLETYPE * a_dest) const
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		memcpy(&a_dest[i * segment_length], &m_Sections[i]->m_BlockMeta, sizeof(NIBBLETYPE) * segment_length);
	}
}





void cChunkBuffer::CopyLight(NIBBLETYPE * a_dest) const
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		memcpy(&a_dest[i * segment_length], &m_Sections[i]->m_BlockLight, sizeof(NIBBLETYPE) * segment_length);
	}
}





void cChunkBuffer::CopySkyLight(NIBBLETYPE * a_dest) const
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		memcpy(&a_dest[i * segment_length], &m_Sections[i]->m_BlockSkyLight, sizeof(NIBBLETYPE) * segment_length);
	}
}





void cChunkBuffer::SetBlocks(const BLOCKTYPE * a_src)
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		if (m_Sections[i])
		{
			memcpy(&m_Sections[i]->m_BlockTypes, &a_src[i * segment_length], sizeof(BLOCKTYPE) * segment_length);
		}
	} 
}




void cChunkBuffer::SetMeta(const NIBBLETYPE * a_src)
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		if (m_Sections[i])
		{
			memcpy(&m_Sections[i]->m_BlockMeta, &a_src[i * segment_length], sizeof(NIBBLETYPE) * segment_length);
		}
	} 
}




void cChunkBuffer::SetLight(const NIBBLETYPE * a_src)
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		if (m_Sections[i])
		{
			memcpy(&m_Sections[i]->m_BlockLight, &a_src[i * segment_length], sizeof(NIBBLETYPE) * segment_length);
		}
	} 
}




void cChunkBuffer::SetSkyLight  (const NIBBLETYPE * a_src)
{
	for (int i = 0; i < CHUNK_SECTION_NUM; i++)
	{
		const size_t segment_length = CHUNK_SECTION_HEIGHT * 16 * 16 / 2;
		if (m_Sections[i])
		{
			memcpy(&m_Sections[i]->m_BlockSkyLight, &a_src[i * segment_length], sizeof(NIBBLETYPE) * segment_length);
		}
	} 
}





cChunkBuffer::sChunkSection * cChunkBuffer::Allocate() const
{
	// TODO: use a allocation pool
	return new cChunkBuffer::sChunkSection;
}
