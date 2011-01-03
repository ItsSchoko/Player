/////////////////////////////////////////////////////////////////////////////
// This file is part of EasyRPG Player.
//
// EasyRPG Player is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EasyRPG Player is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include "sprite.h"
#include "player.h"
#include "graphics.h"
#include "util_macro.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Sprite::Sprite() :
	type(TypeSprite),
	ID(Graphics::drawable_id++),
	bitmap(NULL),
	visible(true),
	x(0),
	y(0),
	z(0),
	ox(0),
	oy(0),
	flash_duration(0),
	flash_frame(0) {

	bitmap_screen = BitmapScreen::CreateBitmapScreen(false);

	zobj = Graphics::RegisterZObj(0, ID);
	Graphics::RegisterDrawable(ID, this);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Sprite::~Sprite() {
	Graphics::RemoveZObj(ID);
	Graphics::RemoveDrawable(ID);
	delete bitmap_screen;
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Sprite::Draw(int z_order) {
	if (!visible) return;
	if (GetWidth() <= 0 || GetHeight() <= 0) return;
	if ((x - ox) < -GetWidth() || (x - ox) > DisplayUi->GetWidth() || (y - oy) < -GetHeight() || (y - oy) > DisplayUi->GetHeight()) return;

	bitmap_screen->BlitScreen(x - ox, y - oy, src_rect);
}

////////////////////////////////////////////////////////////
int Sprite::GetWidth() const {
	return src_rect.width;
}

////////////////////////////////////////////////////////////
int Sprite::GetHeight() const {
	return src_rect.height;
}

////////////////////////////////////////////////////////////
void Sprite::Update() {
	if (flash_duration != 0) {
		flash_frame += 1;
		if (flash_duration == flash_frame) {
			flash_duration = 0;
			bitmap_screen->SetFlashEffect(Color(), 0);
		} else {
			bitmap_screen->UpdateFlashEffect(flash_frame);
		}
	}
}

////////////////////////////////////////////////////////////
void Sprite::Flash(int duration){
	bitmap_screen->SetFlashEffect(Color(0, 0, 0, 0), duration);
	flash_duration = duration;
	flash_frame = 0;
}
void Sprite::Flash(Color color, int duration){
	bitmap_screen->SetFlashEffect(color, duration);
	flash_duration = duration;
	flash_frame = 0;
}

////////////////////////////////////////////////////////////
Bitmap* Sprite::GetBitmap() const {
	return bitmap;
}

void Sprite::SetBitmap(Bitmap* nbitmap) {
	bitmap = nbitmap;
	if (!bitmap) {
		src_rect = Rect();
	} else {
		src_rect = bitmap->GetRect();
	}
	bitmap_screen->SetBitmap(bitmap);
	bitmap_screen->SetSrcRect(src_rect);
}
Rect Sprite::GetSrcRect() const {
	return src_rect;
}

void Sprite::SetSrcRect(Rect nsrc_rect) {
	src_rect = nsrc_rect;
}
void Sprite::SetSpriteRect(Rect nsprite_rect) {
	bitmap_screen->SetSrcRect(nsprite_rect);
}

bool Sprite::GetVisible() const {
	return visible;
}
void Sprite::SetVisible(bool nvisible) {
	visible = nvisible;
}

int Sprite::GetX() const {
	return x;
}
void Sprite::SetX(int nx) {
	x = nx;
}

int Sprite::GetY() const {
	return y;
}
void Sprite::SetY(int ny) {
	y = ny;
}

int Sprite::GetZ() const {
	return z;
}
void Sprite::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZObj(zobj, nz);
	z = nz;
}

int Sprite::GetOx() const {
	return ox;
}
void Sprite::SetOx(int nox) {
	ox = nox;
}

int Sprite::GetOy() const {
	return oy;
}
void Sprite::SetOy(int noy) {
	oy = noy;
}

double Sprite::GetZoomX() const {
	return bitmap_screen->GetZoomXEffect();
}
void Sprite::SetZoomX(double zoom_x) {
	bitmap_screen->SetZoomXEffect(zoom_x);
}

double Sprite::GetZoomY() const {
	return bitmap_screen->GetZoomYEffect();
}
void Sprite::SetZoomY(double zoom_y) {
	bitmap_screen->SetZoomXEffect(zoom_y);
}

double Sprite::GetAngle() const {
	return bitmap_screen->GetAngleEffect();
}
void Sprite::SetAngle(double angle) {
	bitmap_screen->SetAngleEffect(angle);
}

bool Sprite::GetFlipX() const {
	return bitmap_screen->GetFlipXEffect();
}
void Sprite::SetFlipX(bool flipx) {
	bitmap_screen->SetFlipXEffect(flipx);
}

bool Sprite::GetFlipY() const {
	return bitmap_screen->GetFlipYEffect();
}
void Sprite::SetFlipY(bool flipy) {
	bitmap_screen->SetFlipYEffect(flipy);
}

int Sprite::GetBushDepth() const {
	return bitmap_screen->GetBushDepthEffect();
}
void Sprite::SetBushDepth(int bush_depth) {
	bitmap_screen->SetBushDepthEffect(bush_depth);
}

int Sprite::GetOpacity() const {
	return bitmap_screen->GetOpacityEffect();
}
void Sprite::SetOpacity(int opacity) {
	bitmap_screen->SetOpacityEffect(opacity);
}

int Sprite::GetBlendType() const {
	return bitmap_screen->GetBlendType();
}
void Sprite::SetBlendType(int blend_type) {
	bitmap_screen->SetBlendType(blend_type);
}

Color Sprite::GetBlendColor() const {
	return bitmap_screen->GetBlendColor();
}
void Sprite::SetBlendColor(Color color) {
	bitmap_screen->SetBlendColor(color);
}

Tone Sprite::GetTone() const {
	return bitmap_screen->GetToneEffect();
}
void Sprite::SetTone(Tone tone) {
	bitmap_screen->SetToneEffect(tone);
}

////////////////////////////////////////////////////////////
unsigned long Sprite::GetId() const {
	return ID;
}

DrawableType Sprite::GetType() const {
	return type;
}
