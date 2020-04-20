class SchanaHeadingMenu extends UIScriptedMenu
{
    private Widget m_SchanaHeadingRootWidget;
    private TextWidget m_SchanaHeadingTextWidget;
    private bool m_SchanaIsVisible;

    void SchanaHeadingMenu(bool visible)
    {
        m_SchanaHeadingRootWidget = GetGame().GetWorkspace().CreateWidgets("SchanaModCompass/GUI/Layouts/compass.layout");
        m_SchanaHeadingTextWidget = TextWidget.Cast(m_SchanaHeadingRootWidget);
        m_SchanaIsVisible = visible;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SchanaUpdate, 1, true);
    }

    void ~SchanaHeadingMenu()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SchanaUpdate);
        if (m_SchanaHeadingRootWidget != null)
        {
            m_SchanaHeadingRootWidget.Show(false);
        }
    }

    void SchanaUpdate()
    {
        if (m_SchanaIsVisible && m_SchanaHeadingRootWidget != null && GetGame().GetPlayer())
        {
            m_SchanaHeadingTextWidget.SetText(SchanaGetHeading());
            m_SchanaHeadingRootWidget.Update();
            m_SchanaHeadingRootWidget.Show(true);
        }
        else if (m_SchanaHeadingRootWidget != null)
        {
            m_SchanaHeadingRootWidget.Show(false);
        }
    }

    string SchanaGetHeading()
    {
        vector direction = GetGame().GetCurrentCameraDirection();
        float angle = direction.VectorToAngles()[0];
        float rounded = Math.Round(5 * Math.Round(angle / 5.0));
        return rounded.ToString();
    }

    void SchanaSetHeadingVisible(bool visible)
    {
        m_SchanaIsVisible = visible;
    }

    void SchanaToggleHeading()
    {
        m_SchanaIsVisible = !m_SchanaIsVisible;
    }
}
