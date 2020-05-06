class SchanaHeadingMenu extends UIScriptedMenu {
    private Widget m_SchanaHeadingRootWidget;
    private TextWidget m_SchanaHeadingTextWidget;
    private Widget m_SchanaCompassFrameWidget;
    private ImageWidget m_SchanaCompassImageWidget;
    private bool m_SchanaIsVisible;
    private bool m_SchanaHeadingVisible = false;

    void SchanaHeadingMenu (bool visible) {
        m_SchanaHeadingRootWidget = GetGame ().GetWorkspace ().CreateWidgets ("SchanaModCompass/GUI/Layouts/compass.layout");
        m_SchanaHeadingTextWidget = TextWidget.Cast (m_SchanaHeadingRootWidget.FindAnyWidget ("TextHeading"));
        m_SchanaCompassFrameWidget = m_SchanaHeadingRootWidget.FindAnyWidget ("FrameCompass");
        m_SchanaCompassImageWidget = ImageWidget.Cast (m_SchanaHeadingRootWidget.FindAnyWidget ("ImageCompass"));
        m_SchanaIsVisible = visible;

        GetGame ().GetCallQueue (CALL_CATEGORY_GUI).CallLater (this.SchanaUpdate, 16, true);
    }

    void ~SchanaHeadingMenu () {
        GetGame ().GetCallQueue (CALL_CATEGORY_GUI).Remove (this.SchanaUpdate);
        if (m_SchanaHeadingRootWidget != null) {
            m_SchanaHeadingRootWidget.Show (false);
        }
    }

    void SchanaUpdate () {
        if (m_SchanaIsVisible && m_SchanaHeadingRootWidget != null && GetGame ().GetPlayer ()) {
            float angle = SchanaGetAngle ();

            m_SchanaCompassFrameWidget.Show (!m_SchanaHeadingVisible);
            m_SchanaHeadingTextWidget.Show (m_SchanaHeadingVisible);

            m_SchanaHeadingTextWidget.SetText (SchanaGetHeading (angle));
            SchanaSetCompassPos (angle);
            m_SchanaHeadingRootWidget.Update ();
            m_SchanaHeadingRootWidget.Show (true);
        } else if (m_SchanaHeadingRootWidget != null) {
            m_SchanaHeadingRootWidget.Show (false);
        }
    }

    string SchanaGetHeading (float angle) {
        float rounded = Math.Round (5 * Math.Round (angle / 5.0));
        return rounded.ToString ();
    }

    void SchanaSetCompassPos (float angle) {
        float width, height, x, y;
        m_SchanaCompassImageWidget.GetPos (x, y);
        m_SchanaCompassImageWidget.GetSize (width, height);

        float center_offset = width / -2.0 + 0.5;

        if (angle > 180) {
            angle = angle - 360;
        }
        float offset = angle * (center_offset / 180.0) + center_offset;

        m_SchanaCompassImageWidget.SetPos (offset, y);
    }

    float SchanaGetAngle () {
        vector direction = GetGame ().GetCurrentCameraDirection ();
        float angle = direction.VectorToAngles () [0];
        return angle;
    }

    void SchanaSetHeadingVisible (bool visible) {
        m_SchanaIsVisible = visible;
    }

    void SchanaToggleHeading () {
        if (!m_SchanaIsVisible) {
            m_SchanaIsVisible = true;
        } else {
            if (m_SchanaHeadingVisible) {
                m_SchanaIsVisible = false;
            }
            m_SchanaHeadingVisible = !m_SchanaHeadingVisible;
        }
    }
}