#pragma once

#include "IInputDevice.h"
#include "IMouseBackend.h"
#include "MouseState.h"
#include "MouseDeltaState.h"
#include "MouseButton.h"

**
 * @brief Kelas MouseInputDevice bertanggung jawab menerima input dari backend dan menyimpan state mouse.
 */
class MouseInputDevice : public IInputDevice {
public:
    explicit MouseInputDevice(IMouseBackend* backend);
    virtual ~MouseInputDevice();

    /**
     * @brief Update state mouse dan delta-nya.
     */
    void update(); // override

    /**
     * @brief Mengambil state mouse saat ini (posisi, tombol).
     */
    const MouseState& getState() const;

    /**
     * @brief Mengambil delta movement state (perubahan posisi).
     */
    const MouseDeltaState& getDelta() const;

	bool isMouseDown(GE::MouseButton button) const;
	bool isMouseUp(GE::MouseButton button) const;
	bool isMouseHeld(GE::MouseButton button) const;

private:
    MouseState state;
    MouseState prevState;
    MouseDeltaState delta;

    IMouseBackend* backend;
};
