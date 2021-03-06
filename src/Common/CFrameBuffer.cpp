#include "stdafx.h"
#include "CFrameBuffer.h"
#include "CTexture2D.h"

#include "glad.h"
#include "CGraphics.h"

CFrameBuffer::CFrameBuffer( uint32 nWidth, uint32 nHeight )
{
	glGenFramebuffers( 1, &m_nFrameBuffer );
	CheckError();
	BindFrame();

	GLenum nAttachment[eBufferType_Count] =
	{
		GL_COLOR_ATTACHMENT0,
		GL_DEPTH_ATTACHMENT
	};
	for ( uint32 i = 0; i < eBufferType_Count; ++i )
	{
		m_aryTexture[i] = new CTexture2D();
		m_aryTexture[i]->SetTextureData( eIF_RGBA, nWidth, nHeight, nullptr );
		uint32 nTextureID = m_aryTexture[i]->GetTextureID();
		glFramebufferTexture2D( GL_FRAMEBUFFER, nAttachment[i], GL_TEXTURE_2D, nTextureID, 0 );
		CheckError();
	}

	UnBindFrame();
}

CFrameBuffer::~CFrameBuffer()
{
	for ( uint32 i = 0; i < eBufferType_Count; ++i )
		SAFE_DELETE( m_aryTexture[i] );

	glDeleteFramebuffers( 1, &m_nFrameBuffer );
	CheckError();
	m_nFrameBuffer = 0;
}

void CFrameBuffer::BindFrame()
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_nFrameBuffer );
	CheckError();
}

void CFrameBuffer::UnBindFrame()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	CheckError();
}

void CFrameBuffer::CloseBuffer()
{
	BindFrame();
	glClearColor( 0.0f, 0.0f, 0.0f,1.0f );
	CheckError();
	glClear( GL_COLOR_BUFFER_BIT );
	CheckError();
	UnBindFrame();
}
